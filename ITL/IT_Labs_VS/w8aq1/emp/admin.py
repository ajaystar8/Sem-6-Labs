from django.contrib import admin
from .models import HumanModel

# Register your models here.
class HumanAdmin(admin.ModelAdmin):
    list_display = ('fname','lname', 'phone', 'addr', 'city')
admin.site.register(HumanModel, HumanAdmin)