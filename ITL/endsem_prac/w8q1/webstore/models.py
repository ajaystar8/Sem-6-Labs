from django.db import models

# Create your models here.
class CategoryModel(models.Model):
    name = models.CharField(max_length=100)
    visits = models.PositiveIntegerField()
    likes = models.PositiveIntegerField()

class PageModel(models.Model):
    category = models.CharField(max_length=100)
    title = models.CharField(max_length=100)
    url = models.URLField()
    views = models.PositiveIntegerField()
