from django.contrib import admin
from django.urls import path, include

admin.autodiscover()

urlpatterns = [
    path('', include('books.urls')),
    path('admin/', admin.site.urls),
]
