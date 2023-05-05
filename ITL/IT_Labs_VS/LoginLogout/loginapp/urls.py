from django.urls import path
from . import views

urlpatterns = [
    path('connection/', views.connection, name="login"), 
    path('loggedin/', views.loggedin, name = 'loggedin'),
    path('logout/', views.logout, name = "logout"),
]