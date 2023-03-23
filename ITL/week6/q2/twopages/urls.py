from django.urls import path
from . import views

urlpatterns = [
    path('info/', views.index, name='info'),
    path('display/', views.display, name='display'),
]
