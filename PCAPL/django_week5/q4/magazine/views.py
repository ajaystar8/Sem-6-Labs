from django.shortcuts import render

# Create your views here.


def make_magazine(request):
    return render(request, 'form.html')
