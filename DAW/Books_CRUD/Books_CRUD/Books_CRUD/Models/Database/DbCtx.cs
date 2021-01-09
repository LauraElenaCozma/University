using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace Books_CRUD.Models.Database
{
    public class DbCtx : DbContext
    {
        public DbCtx() : base("BooksCS")
        {
            System.Data.Entity.Database.SetInitializer<DbCtx>(
                new Initp());
        }

        public DbSet<Book> Books { get; set; }
        public DbSet<Publisher> Publishers { get; set; }
        public DbSet<ContactInfo>  ContactInfos { get; set; }
        public DbSet<BookType> BookTypes { get; set; }
    }

    public class Initp : DropCreateDatabaseIfModelChanges<DbCtx>
    {
        protected override void Seed(DbCtx context)
        {
            context.Books.Add(new Book { 
                Title = "Pride and Prejudice", 
                Author = "Jane Austen", 
                Summary = "aaa vvvvv dddddd sssssss"});

            context.Books.Add(new Book
            {
                Title = "Gone with the wind",
                Author = "Margaret Mitchell",
            });
            
            context.SaveChanges();
            base.Seed(context);
        }
    }
}