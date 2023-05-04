from django import forms
from books.models import AuthorModel, PublisherModel, BookModel


class AuthorModelForm(forms.ModelForm):
    class Meta:
        model = AuthorModel
        exclude = ('',)


class PublisherModelForm(forms.ModelForm):
    class Meta:
        model = PublisherModel
        exclude = ('',)


class BookModelForm(forms.ModelForm):
    class Meta:
        model = BookModel
        exclude = ('',)
