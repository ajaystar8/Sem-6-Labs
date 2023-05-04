from django.db import models

# Create your models here.


class EmpModel(models.Model):
    index = models.PositiveIntegerField()
    name = models.CharField(max_length=100)
    company = models.CharField(max_length=100)
    salary = models.PositiveIntegerField()
    street = models.CharField(max_length=100)
    city = models.CharField(max_length=100)

    class Meta:
        ordering = ("index", )
