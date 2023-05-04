from django.shortcuts import render
from .models import CategoryModel, PageModel
from .forms import CategoryModelForm, PageModelForm

# Create your views here.
def archive(request):
    cat_list = CategoryModel.objects.all()
    page_list = PageModel.objects.all()
    return render(request, "archive.html", {'categories': cat_list, 'pages':page_list})

def category(request):
    new_form = CategoryModelForm()
    if request.method == 'POST':
        response = CategoryModelForm(request.POST)
        if response.is_valid():
            response.save()
        return render(request, "category.html", {'form':new_form})
    else: 
        return render(request, "category.html", {'form':new_form})

def page(request):
    new_form = PageModelForm()
    if request.method == 'POST':
        response = PageModelForm(request.POST)
        if response.is_valid():
            response.save()
        return render(request, "page.html", {'form':new_form})
    else: 
        return render(request, "page.html", {'form':new_form})