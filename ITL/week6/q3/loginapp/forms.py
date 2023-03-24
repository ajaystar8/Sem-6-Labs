from django import forms


class LoginForm(forms.Form):
    username = forms.CharField(max_length=100, required=True)
    password = forms.CharField(widget=forms.PasswordInput(), required=False)
    email = forms.EmailField(required=False)
    contact = forms.CharField(max_length=10, required=False)
