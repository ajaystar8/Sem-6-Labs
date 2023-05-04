from django.shortcuts import render
from django.http import HttpResponseRedirect

from sites.models import CategoryModel, PageModel
from sites.forms import CategoryForm, PageForm

# Create your views here.


def index(request):
    categories = CategoryModel.objects.all()
    pages = PageModel.objects.all()
    return render(request, "dir.html", {'categories': categories, 'pages': pages, 'cat_form': CategoryForm(), 'page_form': PageForm()})


def create(request):
    if request.method == "POST":
        cat_form = CategoryForm(request.POST)
        page_form = PageForm(request.POST)

        if cat_form.is_valid() and page_form.is_valid():
            cat = cat_form.save(commit=False)
            page = page_form.save(commit=False)

            if CategoryModel.objects.last():
                cat.index = CategoryModel.objects.last().index + 1
                page.index = PageModel.objects.last().index + 1
            else:
                cat.index = 1
                page.index = 1

            cat.save()
            page.save()

    return HttpResponseRedirect('/')
