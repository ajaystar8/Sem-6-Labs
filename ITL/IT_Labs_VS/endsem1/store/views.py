from django.shortcuts import render
from .models import BookModel, IssueBookModel
from .forms import BookModelForm, IssueBookModelForm, LoginForm
from django.http import HttpResponse, HttpResponseRedirect

# Create your views here.
def login(request):
    uname = 'none'
    num = 'none'
    if request.method == "POST":
        form = LoginForm(request.POST)
        if form.is_valid():
            uname = form.cleaned_data['uname']
            num = form.cleaned_data['num']
            return render(request, 'add.html', {'uname':uname, 'num':num})
    else:
        new_form = LoginForm()
        return render(request, 'login.html', {'new_form':new_form})


def addBook(request):
    new_form = BookModelForm()
    if request.method == "POST":
        form = BookModelForm(request.POST)
        if form.is_valid():
            form.save()
        books = BookModel.objects.all()
        return render(request, "add.html", {'new_form': new_form, 'books': books})
    else: 
        books = BookModel.objects.all()
        return render(request, "add.html", {'new_form': new_form, 'books': books})

def issueBook(request):
    new_form = IssueBookModelForm()
    if request.method == 'POST': 
        form = IssueBookModelForm(request.POST)
        if form.is_valid(): 
            form.save()
        issued_books = IssueBookModel.objects.all()
        return render(request, "issue.html", {'new_form': new_form, 'issued_books': issued_books})
    else: 
        issued_books = IssueBookModel.objects.all()
        return render(request, "issue.html", {'new_form': new_form, 'issued_books': issued_books})

def getBook(request):
    if request.method == "POST":
        author = request.POST["author"]
        if author: 
            books = BookModel.objects.filter(author = author)
            return render(request, 'filter_author.html', {'books':books})
    return HttpResponse("<h1>No book found. </h1>")

def getIssuer(request):
    if request.method == "POST":
        iname = request.POST["iname"]
        if iname: 
            books = IssueBookModel.objects.filter(iname = iname)
            return render(request, 'filter_issuer.html', {'books':books})
    return HttpResponse("<h1>No issuer found. </h1>")


def delete(request, name):
    BookModel.objects.get(name = name).delete()
    return HttpResponseRedirect('/add')

def deleteIssuer(request, iname):
    IssueBookModel.objects.get(iname = iname).delete()
    return HttpResponseRedirect('/issue')