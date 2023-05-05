from django import forms
from .models import BookModel, IssueBookModel

class LoginForm(forms.Form):
    uname = forms.CharField(max_length = 10)
    num = forms.IntegerField()

class BookModelForm(forms.ModelForm):
    class Meta: 
        model = BookModel
        exclude = ()

class IssueBookModelForm(forms.ModelForm):
    class Meta: 
        model = IssueBookModel
        exclude = ()