from django import forms
from . import models


class EmpModelForm(forms.ModelForm):
    class Meta:
        model = models.EmpModel
        exclude = ("index", )
