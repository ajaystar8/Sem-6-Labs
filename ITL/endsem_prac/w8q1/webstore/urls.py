from django.urls import path
from . import views

urlpatterns = [
    path('', views.archive, name='archive'),
    path('category/', views.category, name='category'),
    path('page/', views.page, name='page'),
]