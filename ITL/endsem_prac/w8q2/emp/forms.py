from django import forms
from .models import WorksModel, LivesModel

class WorksModelForm(forms.ModelForm):
    class Meta: 
        model = WorksModel
        exclude = ("empid",)

class LivesModelForm(forms.ModelForm):
    class Meta: 
        model = LivesModel
        exclude = ()