# Generated by Django 2.2.28 on 2023-05-04 19:10

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('store', '0002_auto_20230505_0033'),
    ]

    operations = [
        migrations.AlterField(
            model_name='issuebookmodel',
            name='bname',
            field=models.CharField(max_length=100),
        ),
    ]
