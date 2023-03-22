from django.shortcuts import render

# Create your views here.


def render_form(request):
    return render(request, 'form.html')
