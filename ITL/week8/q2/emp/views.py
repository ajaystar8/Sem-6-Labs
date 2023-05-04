from django.shortcuts import render
from django.http import HttpResponse, HttpResponseRedirect

from emp.models import EmpModel
from emp.forms import EmpModelForm

# Create your views here.


def index(request):
    emp_list = EmpModel.objects.all()
    emp_form = EmpModelForm()
    return render(request, 'index.html', {'emp_list': emp_list, 'form': emp_form})


def add(request):
    if request.method == "POST":
        emp_detail = EmpModelForm(request.POST)
        if emp_detail.is_valid():
            emp = emp_detail.save(commit=False)
            if EmpModel.objects.last():
                emp.index = EmpModel.objects.last().index + 1
            else:
                emp.index = 1
            emp.save()
    return HttpResponseRedirect("/")


def get(request):
    if request.method == "POST":
        company = request.POST['company']
        if company:
            emps = EmpModel.objects.filter(company=company)
            return render(request, 'filter.html', {'emps': emps})
    return HttpResponse("<h1> Company doesn't exist. </h1>")
