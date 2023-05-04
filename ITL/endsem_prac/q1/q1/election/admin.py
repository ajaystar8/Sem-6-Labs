from django.contrib import admin
from .models import CandidateModel, VotingModel

# Register your models here.
class CandidateAdmin(admin.ModelAdmin):
    list_display = ('name','section')
admin.site.register(CandidateModel, CandidateAdmin)

class VotingAdmin(admin.ModelAdmin):
    list_display = ('name','vote')
admin.site.register(VotingModel, VotingAdmin)
