from django.db import models

# Create your models here.
class BookModel(models.Model): 
    name = models.CharField(max_length = 100)
    author = models.CharField(max_length = 100)

    def __str__(self):
        return self.name

class IssueBookModel(models.Model):
    iname = models.CharField(max_length = 100)
    bname = models.ForeignKey(BookModel, on_delete = models.CASCADE)

    def __str__(self):
        return self.bname