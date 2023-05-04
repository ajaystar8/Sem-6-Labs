from django import forms
from .models import CategoryModel, PageModel

class CategoryModelForm(forms.ModelForm): 
    class Meta: 
        model = CategoryModel
        exclude = ()

class PageModelForm(forms.ModelForm): 
    class Meta: 
        model = PageModel
        exclude = ()  