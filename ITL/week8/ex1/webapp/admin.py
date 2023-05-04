from django.contrib import admin
from webapp import models


class BlogPostAdmin(admin.ModelAdmin):
    list_display = ('title', 'timestamp')


admin.site.register(models.BlogPost, BlogPostAdmin)
