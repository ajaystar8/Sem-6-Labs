from django.urls import path
from . import views

urlpatterns = [
    path('elect/', views.candidates, name = 'elect'),
]