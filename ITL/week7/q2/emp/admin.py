from django.contrib import admin
from emp.models import EmpModel

# Register your models here.


class EmpAdmin(admin.ModelAdmin):
    list_display = ('name', 'company', 'salary', 'street', 'city')


admin.site.register(EmpModel, EmpAdmin)
