"""
URL configuration for backend project.

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/5.0/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path, re_path
from . import views
from .views import *

urlpatterns = [
    path('', index, name='index'),
    path('registerUsername', views.register_username, name='registerUsername'),
    path('save_game_result', views.save_game_result, name='save_game_result'),
    path('print_all_records', views.print_all_records, name='print_all_records'),
    path('get_game_history', views.get_game_history, name='get_game_history'),
    re_path(r'^.*/$', index, name='app'), # catch all urls
]
