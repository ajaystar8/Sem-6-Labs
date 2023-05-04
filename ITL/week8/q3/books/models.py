from django.db import models

# Create your models here.


class AuthorModel(models.Model):
    fname = models.CharField(max_length=100)
    lname = models.CharField(max_length=100)
    email = models.EmailField()

    class Meta:
        ordering = ("fname", )


class PublisherModel(models.Model):
    name = models.CharField(max_length=100)
    address = models.TextField()
    city = models.CharField(max_length=100)
    state = models.CharField(max_length=100)
    country = models.CharField(max_length=100)
    website = models.URLField()

    class Meta:
        ordering = ("name", )


class BookModel(models.Model):
    title = models.CharField(max_length=100)
    date = models.DateField()
    authors = models.ForeignKey(AuthorModel, on_delete=models.CASCADE)
    publisher = models.OneToOneField(PublisherModel, on_delete=models.CASCADE)

    class Meta:
        ordering = ("title", )
