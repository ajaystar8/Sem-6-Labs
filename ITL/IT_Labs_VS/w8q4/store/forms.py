from django import forms
from . models import ProductModel

class ProductModelForm(forms.ModelForm):
    class Meta: 
        model = ProductModel
        exclude = ()