from django.shortcuts import render
from loginapp.forms import LoginForm

# Create your views here.


def login(request):
    form = LoginForm()
    return render(request, "login.html", {'form': form})


def loggedin(request):
    if request.method == "POST":
        reg_info = LoginForm(request.POST)
        if reg_info.is_valid():
            username = reg_info.cleaned_data['username']
            email = reg_info.cleaned_data['email']
            contact = reg_info.cleaned_data['contact']
            request.session['username'] = username
            request.session['email'] = email
            request.session['contact'] = contact
        return render(request, 'loggedin.html', {'username': username, 'email': email, 'contact': contact})
