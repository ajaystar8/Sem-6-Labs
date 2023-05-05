from django.shortcuts import render
from .models import WorksModel, LivesModel
from .forms import WorksModelForm, LivesModelForm

# Create your views here
def works(request):
    new_form = WorksModelForm()
    if request.method == "POST":
        form = WorksModelForm(request.POST)
        if form.is_valid():
            form.save()
        emps = WorksModel.objects.all()
        return render(request, "works.html", {'new_form': new_form, 'emps': emps})
    else:
        emps = WorksModel.objects.all()
        return render(request, "works.html", {'new_form': new_form, 'emps': emps})

def lives(request):
    new_form = LivesModelForm()
    if request.method == "POST":
        form = LivesModelForm(request.POST)
        if form.is_valid():
            form.save()
        emps = LivesModel.objects.all()
        return render(request, "lives.html", {'new_form': new_form, 'emps': emps})
    else:
        emps = LivesModel.objects.all()
        return render(request, "lives.html", {'new_form': new_form, 'emps': emps})

def filter(request):
    if request.method == "POST":
        cname = request.POST['cname']
        if cname: 
            emps = WorksModel.objects.filter(cname = cname)
            return render(request, 'filter.html', {'emps':emps})
    return HttpResponse("<h1> No Employee found. </h1>")
