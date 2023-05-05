from django.urls import path
from . import views

urlpatterns = [
    path('works/', views.works, name = "works"),
    path('lives/', views.lives, name = "lives"),
    path('filter/', views.filter, name = "filter"),
]