from django.contrib import admin
from .models import WorksModel, LivesModel 

# Register your models here.
class WorksAdmin(admin.ModelAdmin):
    list_display = ('empid', 'pname', 'cname', 'salary')
admin.site.register(WorksModel, WorksAdmin)

class LivesAdmin(admin.ModelAdmin):
    list_display = ('empid', 'street', 'city')
admin.site.register(LivesModel, LivesAdmin)
