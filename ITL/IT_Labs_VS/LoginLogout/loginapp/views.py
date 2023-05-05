from django.shortcuts import render
from .forms import LoginForm
from django.http import HttpResponse

# Create your views here.
def connection(request):
    uname = 'none'
    if request.method == "POST":
        form = LoginForm(request.POST)
        if form.is_valid():
            uname = form.cleaned_data['uname']
            request.session['uname'] = uname
        return render(request, 'loggedin.html', {'uname':uname})  
    else:
        new_form = LoginForm()
        return render(request, 'connection.html', {'new_form':new_form})  

def loggedin(request):
    if request.session.has_key('uname'):
        uname = request.session['uname']
        return render(request, 'loggedin.html', {'uname':uname})  
    else:
        new_form = LoginForm()
        return render(request, 'connection.html', {'new_form':new_form})  

def logout(request):
    try: 
        del request.session['uname']
    except:
        pass
    return HttpResponse("<strong>You are logged out.</strong>")