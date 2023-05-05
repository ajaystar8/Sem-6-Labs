from django.shortcuts import render
from .models import StudentModel
from .forms import StudentModelForm
from django.http import HttpResponse

# Create your views here.
def home(request):
    new_form = StudentModelForm()
    if request.method == "POST":
        form = StudentModelForm(request.POST)
        if form.is_valid():
            form.save()
            return render(request, 'home.html', {'new_form':new_form})
    else:  
        return render(request, 'home.html', {'new_form':new_form})

def display(request):
    students = StudentModel.objects.all()
    return render(request, 'display.html', {'students':students})

def filter(request):
    if request.method == 'POST':
        regno = request.POST['regno']
        print(f'{regno}\n')
        if regno: 
            target_student = StudentModel.objects.filter(regno = regno)
            for dt in target_student:
                print(f'{dt.name}\n')
            return render(request, 'filter.html', {'target_student':target_student})
    else:
        return HttpResponse("<h1> Company doesn't exist. </h1>")