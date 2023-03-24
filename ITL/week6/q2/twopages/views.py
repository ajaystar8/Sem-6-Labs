from django.shortcuts import render
from twopages.forms import StudentInfoForm

# Create your views here.


def index(request):
    form = StudentInfoForm()
    return render(request, 'index.html', {'form': form})


def display(request):
    name = None
    roll = None
    subject = None
    student_info = StudentInfoForm(request.POST)
    if student_info.is_valid():
        name = student_info.cleaned_data['name']
        roll = student_info.cleaned_data['roll']
        subject = student_info.cleaned_data['subject']
        request.session['name'] = name
        request.session['roll'] = roll
        request.session['subject'] = subject
    return render(request, 'display.html', {'name': name, 'roll': roll, 'subject': subject})
