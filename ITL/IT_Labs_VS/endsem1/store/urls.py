from django.urls import path
from . import views

urlpatterns = [
    path('login/', views.login, name = "login"),
    path('add/', views.addBook, name = "add"), 
    path('issue/', views.issueBook, name = "issue"), 
    path('filter_author/', views.getBook, name = "filter_author"),
    path('filter_issuer/', views.getIssuer, name = "filter_issuer"),
    path('delete/<str:name>', views.delete, name = "name"),
    path('deleteIssuer/<str:iname>', views.deleteIssuer, name = "iname"),
]
