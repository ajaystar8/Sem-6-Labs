from django.contrib import admin
from .models import CategoryModel, PageModel

# Register your models here.
class CategoryAdmin(admin.ModelAdmin):
    list_display = ('name', 'visits', 'likes',)
admin.site.register(CategoryModel, CategoryAdmin)

class PageAdmin(admin.ModelAdmin):
    list_display = ('category', 'title', 'url', 'views', )
admin.site.register(PageModel, PageAdmin)