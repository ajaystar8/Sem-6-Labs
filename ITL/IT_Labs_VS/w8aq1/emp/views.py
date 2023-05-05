from django.shortcuts import render
from .models import HumanModel
from .forms import HumanModelForm

# Create your views here.
def human(request):
    new_form = HumanModelForm()
    humans = HumanModel.objects.all()
    return render(request, 'human.html', {'new_form':new_form, 'humans':humans})

def getdetail(request):
    if request.method == "POST":
        fname = request.POST['fname']
        if fname: 
            human = HumanModel.objects.filter(fname = fname)
            return render(request, 'human.html', {'thuman':human})
