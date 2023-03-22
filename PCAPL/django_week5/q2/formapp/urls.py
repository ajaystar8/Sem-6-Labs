from django.urls import path
from . import views

urlpatterns = [
    path('promote', views.check),
]
