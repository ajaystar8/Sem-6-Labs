from django.contrib import admin
from .models import BookModel, IssueBookModel

# Register your models here.
class BookAdmin(admin.ModelAdmin):
    list_display = ('name', 'author')
admin.site.register(BookModel, BookAdmin)

class IssueAdmin(admin.ModelAdmin):
    list_display = ('bname', 'iname')
admin.site.register(IssueBookModel, IssueAdmin)
