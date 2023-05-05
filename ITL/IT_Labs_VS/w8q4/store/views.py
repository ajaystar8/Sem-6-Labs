from django.shortcuts import render
from .models import ProductModel
from .forms import ProductModelForm

# Create your views here.
def add(request):
    new_form = ProductModelForm()
    if request.method == "POST":
        form = ProductModelForm(request.POST)
        if form.is_valid():
            form.save()
        return render(request, 'add.html', {'new_form':new_form})
    else: 
        return render(request, 'add.html', {'new_form':new_form})

def display(request):
    products = ProductModel.objects.all()
    return render(request, 'display.html', {'products':products})

