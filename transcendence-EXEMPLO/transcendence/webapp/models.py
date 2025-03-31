from django.db import models
from django.contrib.auth.models import User
from django.contrib.postgres.fields import ArrayField

# Create your models here.

class GameResult(models.Model):
    # 4 types of games
    GAME_CHOICES = ['PV', 'PT', 'ES', 'ET']

    BO_CHOICES = ['1', '2', '3', '4', '5']

    user = models.ForeignKey(User, on_delete=models.CASCADE)
    game_id = models.CharField(max_length=2, choices=[(choice, choice) for choice in GAME_CHOICES])
    position = ArrayField(models.IntegerField(), size=2)
    date = models.DateTimeField(auto_now_add=True)

    # Additional field for BO type if game ID is ET
    bo_type = models.CharField(max_length=1, choices=[(choice, choice) for choice in BO_CHOICES], blank=True, null=True)

    def __str__(self):
        return f"{self.user.username}'s game {self.game_id} at position {self.position} on {self.date}"
