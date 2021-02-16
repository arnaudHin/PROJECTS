package fr.eseo.poo.projet.artiste.modele.formes;

import static org.junit.Assert.assertEquals;

import java.util.Arrays;
import java.util.Collection;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;

import fr.eseo.poo.projet.artiste.modele.Coordonnees;

@RunWith(Parameterized.class)
public class EllipseTestParametresContient {
	
	private Coordonnees position;
	private double largeur; 
	private double hauteur; 
	private Coordonnees coordContient; 
	private boolean contient;


	
	public EllipseTestParametresContient(Coordonnees position, double largeur, double hauteur, 
			Coordonnees coordContient, boolean contient) {
		this.position = position; 
		this.largeur = largeur; 
		this.hauteur = hauteur;
		this.coordContient = coordContient; 
		this.contient = contient;
	}
	
	@Parameters(name= "dataEllipse[{index}] : {0}, {1}, {2}, {3}, {4}") 
	public static Collection<Object[]>dataEllipse(){
		Object[][] dataEllipse = new Object[][] {
			{new Coordonnees(10, 10), 5, 5, new Coordonnees(12.5, 12.5), true},
			{new Coordonnees(10, 10), 5, 0.2, new Coordonnees(12.5, 10.2), true},
			{new Coordonnees(10, 10), 3, 5, new Coordonnees(11.5, 15), true},
			{new Coordonnees(10, 10), 0.2, 0.2, new Coordonnees(10.1, 10.1), true},
			{new Coordonnees(10, 10), 0.2, 0.2, new Coordonnees(10.1, 10.2), true},
			{new Coordonnees(10, 10), 0.2, 0.2, new Coordonnees(10.2, 10.2), false},
			{new Coordonnees(56.9, 12.3), 16.9, 0.9, new Coordonnees(56.9+2, 12.3 + 0.1), false}
		};
		return Arrays.asList(dataEllipse);}
		
	@Test
	public void testContient() {
		EllipseTestParametresContient testContient = new EllipseTestParametresContient(position, largeur, hauteur, coordContient, contient);
		Ellipse ellipse = new Ellipse(testContient.position, testContient.largeur, testContient.hauteur);
		
		assertEquals("Le point est bien contenu dans l'ellipse", contient, ellipse.contient(coordContient));

	}
		
	
	
	
}
