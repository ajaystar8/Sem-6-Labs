from django.urls import path 
from . import views

urlpatterns = [
    path('home/', views.home, name = 'home'),
    path('display/', views.display, name = 'display'), 
    path('filter/', views.filter, name = 'filter'),
]