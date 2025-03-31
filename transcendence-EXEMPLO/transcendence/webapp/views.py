from django.shortcuts import render
from django.http import JsonResponse
from django.contrib.auth.models import User
from django.db import IntegrityError
from django.utils.html import escape
from datetime import datetime
from django.shortcuts import get_object_or_404
from django.shortcuts import redirect
from .models import GameResult
import json


def index(request):
    return render(request, 'index.html')


def register_username(request):
    is_internal = 'HTTP_REFERER' in request.META
    if not request.path.endswith('/') and not is_internal:
        return redirect(request.path + '/')

    if request.method == 'POST':
        data = json.loads(request.body)
        # username = self.cleaned_data['username']   #Might use this as it is more secure and has more validation
        username = data.get('username')

        # Protection against XSS and SQL injection
        username = escape(username)

        # Validation (make sure username is not empty)
        if not username:
            return JsonResponse({'success': False, 'error': 'Username is required.'})

        # Check if the username already exists
        if User.objects.filter(username=username).exists():
            return JsonResponse({'success': True})


        # Create the user
        try:
            User.objects.create_user(username=username)
            return JsonResponse({'success': True})
        except IntegrityError:
            return JsonResponse({'success': False, 'error': 'Failed to create user.'})
        except Exception as e:  # Catch other potential errors
            return JsonResponse({'success': False, 'error': str(e)})
    else:
        return JsonResponse({'success': False, 'error': 'Invalid request method'})


# saves the games info in a model GameResult, and associates it to the 'username'
def save_game_result(request):
    is_internal = 'HTTP_REFERER' in request.META
    if not request.path.endswith('/') and not is_internal:
        return redirect(request.path + '/')

    if request.method == 'POST':
        try:
            data = json.loads(request.body)
            user_id = data.get('username')
            game_id = data.get('gameHistory', {}).get('game_id')
            position = data.get('gameHistory', {}).get('position')
            date = datetime.now()
            bo_type = data.get('gameHistory', {}).get('bo_type')
            try:
                user = User.objects.get(username=user_id)
            except User.DoesNotExit:
                return JsonResponse({'success': False, 'error': 'User does not exist.'})


            # Create and save a new GameResult instance
            GameResult.objects.create(
                user=user,
                game_id=game_id,
                position=position,
                date=date,
                bo_type=bo_type
            )

            # Return a success response
            return JsonResponse({'success': True})
        except Exception as e:
            # Return an error response if there was an issue
            return JsonResponse({'success': False, 'error': str(e)})
    else:
        # Return an error response for invalid request method
        return JsonResponse({'success': False, 'error': 'Invalid request method'})


# Returns the last 10 games associated to 'username', from game 'game_id'
def get_game_history(request):
    is_internal = 'HTTP_REFERER' in request.META
    if not request.path.endswith('/') and not is_internal:
        return redirect(request.path + '/')

    if request.method == 'GET':
        username = request.GET.get('username')
        game_id = request.GET.get('game_id')
        print('this is the username in the database', username)

        try:
            game_history = GameResult.objects.filter(user__username=username, game_id=game_id).order_by('-date')[:10]
            history_data = [{'user': result.user.username, 'game_id': result.game_id, 'position': result.position, 'date': result.date, 'bo_type': result.bo_type} for result in game_history]

            return JsonResponse(history_data, safe=False)
        except Exception as e:
            return JsonResponse({'error': str(e)}, status=500)
    else:
        return JsonResponse({'error': 'Invalid request method.'}, status=405)


def print_all_records(request):
    is_internal = 'HTTP_REFERER' in request.META
    if not request.path.endswith('/') and not is_internal:
        return redirect(request.path + '/')

    if request.method == 'GET':
        try:
            # Retrieve all users
            all_users = User.objects.all()

            # Retrieve all game results
            all_game_results = GameResult.objects.all()

            # Prepare response data
            user_data = [{'username': user.username} for user in all_users]
            game_result_data = [{'user': result.user.username, 'game_id': result.game_id, 'position': result.position, 'date': result.date, 'bo_type': result.bo_type} for result in all_game_results]

            # Print all records (for debugging purposes)
            for user in all_users:
                print(user)
            for result in all_game_results:
                print(result)

            # Return the response with both sets of data
            return JsonResponse({'users': user_data, 'game_results': game_result_data, 'success': True})
        except Exception as e:
            return JsonResponse({'error': str(e)}, status=500)
    else:
        return JsonResponse({'error': 'Invalid request method.'}, status=405)

