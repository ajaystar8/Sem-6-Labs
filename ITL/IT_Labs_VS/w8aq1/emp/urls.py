from django.urls import path 
from . import views

urlpatterns = [
    path('human/', views.human, name = "human"),
    path('getdetail/', views.getdetail, name = "getdetail")
]