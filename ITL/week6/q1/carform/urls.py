from django.urls import path
from . import views

urlpatterns = [
    path('info/', views.index, name="information"),
    path('display/', views.carInfo, name="display")
]
