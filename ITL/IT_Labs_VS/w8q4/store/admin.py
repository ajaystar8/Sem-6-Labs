from django.contrib import admin
from .models import ProductModel

# Register your models here.
class ProductAdmin(admin.ModelAdmin):
    list_display = ('title', 'price', 'description')
admin.site.register(ProductModel, ProductAdmin)

