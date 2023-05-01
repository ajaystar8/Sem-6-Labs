from django.contrib import admin
from books.models import AuthorModel, PublisherModel, BookModel

# Register your models here.


class AuthorAdmin(admin.ModelAdmin):
    list_display = ("fname", "lname", "email")


admin.site.register(AuthorModel, AuthorAdmin)


class PublisherAdmin(admin.ModelAdmin):
    list_display = ("name", "city", "state", "country")


admin.site.register(PublisherModel, PublisherAdmin)


class BookAdmin(admin.ModelAdmin):
    list_display = ("title", "date")


admin.site.register(BookModel, BookAdmin)
