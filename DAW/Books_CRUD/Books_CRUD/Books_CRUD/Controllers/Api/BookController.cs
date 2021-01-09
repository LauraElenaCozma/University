using Books_CRUD.Models;
using Books_CRUD.Models.Database;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;

namespace Books_CRUD.Controllers.Api
{
    public class BookController : ApiController
    {
        private DbCtx db = new DbCtx();

        //asemanatoare cu actiunea Index
        //https:/ /localhost:44399/api/Book - don't forget to delete the space between / / 
        public List<Book> Get()
        {
            return db.Books.ToList();
        }

        //asemanatoare cu actiunea Details
        // https:/ /localhost:44399/api/Book/1
        public IHttpActionResult Get(int id)
        {
            Book book = db.Books.Find(id);
            if (book == null)
            {
                //returneaza codul 404
                return NotFound();
            }
            //returneaza codul 200, iar in body e cartea
            return Ok(book);
        }

        //echivalent cu New
        //https:/ /localhost:44399/api/Book
        public IHttpActionResult Post([FromBody] Book book)
        {
            db.Books.Add(book);
            db.SaveChanges();

            // helperul Created contine, pe lânga obiectul nou-creat, si adresa la care el va fi gasit
            //redirectionare catre defaultApi
            var uri = new Uri(Url.Link("DefaultApi", new { id = book.BookId }));
            return Created(uri, book);
        }

        //Edit
        //https:/ /localhost:44399/api/Book/2
        public IHttpActionResult Put(int id, [FromBody] Book b)
        {
            Book book = db.Books.Find(id);

            if (book == null)
                return NotFound();

            book.Title = b.Title;
            book.Author = b.Author;
            db.SaveChanges();
            return Ok(book);
        }

        //Delete
        //https:/ /localhost:44399/api/Book/2
        public IHttpActionResult Delete(int id)
        {
            Book book = db.Books.Find(id);

            if (book == null)
                return NotFound();

            db.Books.Remove(book);
            db.SaveChanges();
            return Ok(book);
        }
    }
}
