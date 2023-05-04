from django.db import models

# Create your models here.
class LivesModel(models.Model):
    empid = models.PositiveIntegerField(default=1)
    street = models.CharField(max_length=100)
    city = models.CharField(max_length=100)

class WorksModel(models.Model):
    empid = models.ForeignKey(LivesModel, on_delete=models.CASCADE, default = 1)
    pname = models.CharField(max_length=100)
    cname = models.CharField(max_length=100)
    salary = models.PositiveIntegerField()