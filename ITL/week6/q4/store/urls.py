from django.urls import path
from . import views

urlpatterns = [
    path('shop/', views.shop, name="shop"),
    path('bill/', views.bill, name="bill"),
]
