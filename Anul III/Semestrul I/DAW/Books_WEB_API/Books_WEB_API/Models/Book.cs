using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Web;

namespace Books_WEB_API.Models
{
    [Table("Carti")]
    public class Book
    {
        public int BookId { get; set; }
        public String Title { get; set; }
        public String Author { get; set; }
        public String Summary { get; set; }
        public int? PublisherId { get; set; }
        public virtual Publisher Publisher { get; set; }
        public virtual ICollection<Genre> Genres { get; set; }
        public virtual BookType BookType { get; set; }
    }
}