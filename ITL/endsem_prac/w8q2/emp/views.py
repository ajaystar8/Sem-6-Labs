from django.shortcuts import render
from .forms import WorksModelForm, LivesModelForm
from .models import WorksModel, LivesModel
from django.http import HttpResponse

# Create your views here.
def index(request):
    new_works_form = WorksModelForm()
    new_lives_form = LivesModelForm()
    if request.method == "POST":
        works_form = WorksModelForm(request.POST)
        lives_form = LivesModelForm(request.POST)
        if works_form.is_valid() and lives_form.is_valid():
            works_form.save()
            lives_form.save()
        works_list = WorksModel.objects.all()    
        return render(request, "index.html", {'work_form':new_works_form, 'live_form':new_lives_form, 'works_list':works_list})
    else: 
        works_list = WorksModel.objects.all()    
        return render(request, "index.html", {'work_form':new_works_form, 'live_form':new_lives_form, 'works_list':works_list})
    
def get(request):
    if request.method == "POST":
        company = request.POST["cname"]
        emps = WorksModel.objects.filter(cname = company)
        return render(request, 'get.html', {'emps':emps})
    return HttpResponse("<h1> Company doesn't exist. </h1>")