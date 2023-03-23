from django.shortcuts import render
from carform.forms import CarInfoForm
from django.http import HttpResponse

# Create your views here.


def carInfo(request):
    if request.method == "POST":
        myCarForm = CarInfoForm(request.POST)
        if myCarForm.is_valid():
            context = {
                "carManufacturer": myCarForm.cleaned_data['carManufacturer'],
                "carModel": myCarForm.cleaned_data['carModel']
            }
            return render(request, 'view.html', context)
    return HttpResponse("Invalid Parameters")


def index(request):
    form = CarInfoForm()
    return render(request, "form.html", {'form': form})
