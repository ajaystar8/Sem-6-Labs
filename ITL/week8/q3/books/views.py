from django.shortcuts import render
from django.http import HttpResponse, HttpResponseRedirect

from books.models import AuthorModel, PublisherModel, BookModel
from books.forms import AuthorModelForm, PublisherModelForm, BookModelForm


def index(request):
    authors = AuthorModel.objects.all()
    publishers = PublisherModel.objects.all()
    books = BookModel.objects.all()

    author_form = AuthorModelForm()
    publisher_form = PublisherModelForm()
    book_form = BookModelForm()
    return render(request, "index.html", {'author_form': author_form, 'publisher_form': publisher_form, 'book_form': book_form, 'authors': authors, 'publishers': publishers, 'books': books})


def add(request):
    if request.method == "POST":
        author_form = AuthorModelForm(request.POST)
        publisher_form = PublisherModelForm(request.POST)
        book_form = BookModelForm(request.POST)

        if author_form.is_valid() and publisher_form.is_valid() and book_form.is_valid():
            author = author_form.save(commit=False)
            publisher = publisher_form.save(commit=False)
            book = book_form.save(commit=False)

            author.save()
            publisher.save()
            book.save()
        else:
            print("ERROR")
            print("Authors Valid : ", author_form.is_valid())
            print("Publisher Valid : ", publisher_form.is_valid())
            print("Book Valid : ", book_form.is_valid())
    return HttpResponseRedirect("/")
