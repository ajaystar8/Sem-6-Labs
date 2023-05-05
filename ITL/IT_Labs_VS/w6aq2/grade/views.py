from django.shortcuts import render
from .forms import StudentForm

# Create your views here.
def index(request):
    new_form = StudentForm()
    return render(request, 'index.html', {'new_form':new_form})

def result(request):
   if request.method == "POST":
        form = StudentForm(request.POST)
        if form.is_valid():
            name = form.cleaned_data['name']
            cgpa = (form.cleaned_data['marks'])/50
            context = {'name':name, 'cgpa':cgpa}
            return render(request, 'result.html', context)