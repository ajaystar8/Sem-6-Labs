from django import forms
from .models import HumanModel

class HumanModelForm(forms.ModelForm):
    class Meta: 
        model = HumanModel
        exclude = ()

